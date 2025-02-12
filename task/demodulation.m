file_id = fopen('data.bin', 'rb');
data_raw = fread(file_id, 'int16');
iq = zeros([length(data_raw) / 2 1]);
for i = 1 : length(iq)
    iq(i) = data_raw(i * 2 - 1) + 1i * data_raw(i * 2);
end
demod_data = Demodulate(4, [1; 1; 3; 2], iq)

function [output_data] = Demodulate(M, preamb, iq_raw)
    reshape(dec2bin(preamb)', 1, [])
    N = length(iq_raw);
    p_len = length(preamb);
    iq_preamb = pskmod(preamb, M, pi / M, 'gray');

    % calculate frequency offsets
    ph_deltas = zeros([1, N - 1]);
    for i = 1 : N - 1
        ph_deltas(i) = power(power(iq_raw(i + 1), M) * conj(power(iq_raw(i), M)), 1 / M); 
    end
    

    % remove frequency offsets
    ph_acc = [0 cumsum(angle(ph_deltas))]';
    iq_dedop = iq_raw .* exp(-1i * ph_acc);

    % remove initial phase offset
    initial_phase = sum(iq_dedop(1:p_len) .* conj(iq_preamb)) / sum(abs(iq_dedop(1:p_len)));
    iq_cleared = iq_dedop .* initial_phase';

    % remove psk modulation
    demod_data = pskdemod(iq_cleared, M, pi / M, 'gray');
    demod_data(p_len + 1 : N)'
    output_data = reshape(dec2bin(demod_data(p_len + 1 : N))', 1, []);
end